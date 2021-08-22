#include <vector>


class Sprite {
public:
	int xPos; //position at start of MoveAllSprites
	int yPos; //position at start of MoveAllSprites
	int xVec; //velocity^
	int yVec; //velocity^
	//NEW
	int Travel[2] = {};//expected travel, so the starting velocities, and then slowly whittle down on successes
	int TravelControt[2] = {};
	bool UseControt = false;
	int ExVel[2] = {};
	std::vector<int> LastDestination = {};
	
};

std::vector<Sprite*> AllSprites = {};
std::vector<int> Completed = {0,0,0};


//Goes into LM, figures out the one closest to your travel path, returns it, and figures out appropriate overlap value.
Sprite* JostleX(Sprite* ObjectSprite int& Edge[2]);
Sprite* JostleY(Sprite* ObjectSprite, int& Edge[2]);
Sprite* JostleD(Sprite* ObjectSprite, int& D[2]);

EditTravel(Sprite* ObjectSprite) {
	if (ObjectSprite->UseControt) {
		//edit Controt
	}
	else {
		//edit Travel
	}
}



struct XYArr {
	Sprite* CurrentVictim;
	int XCollision; //might want int
	int YCollision; //might want int
	Sprite* Collisions[3] = { nullptr, nullptr, nullptr }; //x, y, d cases. (what you could be overlapping
	Sprite* HitSprites[3] = {nullptr, nullptr, nullptr}; //what you actually hit/overlap with when calcualted.
};



void CheckFuture3(Sprite* ObjectSprite, XYArr* TempStackable) {
	int Edge[2] = { 0,0 };
	int D[2] = { 0,0 };
	int Final[2] = { 0, 0 } //the values that matter. Figure out how to move for this
	//figure out direction then send to jostle (appropriately!) 
	int Measure; 
	TempStackable->CurrentVictim = ObjectSprite;

	//only do the necessary ones
	TempStackable->Collisions[0] =JostleX(ObjectSprite, Edge);
	TempStackable->Collisions[1] =JostleY(ObjectSprite, Edge);
	TempStackable->Collisions[2] =JostleD(ObjectSprite, D);
	//Edge = {x,y}, D = {Dx, Dy}

	


	int x = Edge[0];
	int y = Edge[1];
	int dx = D[0];
	int dy = D[1];
	//Figure out How to move - Note the Sprite you choose to run into.
	if (Measure == 5 || Measure == 7 || Measure == 13 || Measure == 15) {
		//Diagonal ONLY
		if (x == 0 xor y == 0 && (dx != 0 && dy != 0)) { //Xor gate maybe? on the XY check?
			if (x == 0) {
				if (dy > y) {
					Final[0] = dx;
					Final[1] = y;
					TempStackable->HitSprites[2] = TempStackable->Collisions[2]; //the hit sprite is only equal to whatever you COULD'VE hit.
					TempStackable->HitSprites[1] = TempStackable->Collisions[1]
				}
			}
			if (y == 0) {
				if (dx > x) {
					Final[0] = x;
					Final[1] = dy;
					TempStackable->HitSprites[0] = TempStackable->Collisions[0];
					TempStackable->HitSprites[2] = TempStackable->Collisions[2];
				}
			}
		}
		if (x != 0 && y != 0 && dx != 0 && dy != 0) {
			if (x > dx) {
				Final[0] = x;
				Final[1] = y;
				TempStackable->HitSprites[0] = TempStackable->Collisions[0];
				TempStackable->HitSprites[1] = TempStackable->Collisions[1];
				//exit early if possible
			}
			if (y > dy) {
				Final[0] = x;
				Final[1] = y;
				TempStackable->HitSprites[0] = TempStackable->Collisions[0];
				TempStackable->HitSprites[1] = TempStackable->Collisions[1];
				//Exit early if possible
			}
			if (x == dx && dy == dy) {
				Final[0] = x;
				Final[1] = y;
				TempStackable->HitSprites[0] = TempStackable->Collisions[0];
				TempStackable->HitSprites[1] = TempStackable->Collisions[1];
				TempStackable->HitSprites[2] = TempStackable->Collisions[2];
			}
			if (dy > y && dx > x) {
				Final[0] = dx;
				Final[1] = dy;
				TempStackable->HitSprites[2] = TempStackable->Collisions[2];
			}
		}
		if (x == 0 && y == 0) {
			Final[0] = dx;
			Final[1] = dy;
			TempStackable->HitSprites[2] = TempStackable->Collisions[2]; 
		}
		if (dx == 0 && dy == 0) {
			Final[0] = x;
			Final[0] = y;
			TempStackable->HitSprites[0] = TempStackable->Collisions[0];
			TempStackable->HitSprites[1] = TempStackable->Collisions[1];
		}
	}
	else {
		//Directional ONLY
		if (x != 0) {
			Final[0] = x; 
			TempStackable->HitSprites[0] = TempStackable->Collisions[0];
		}
		if (y != 0) {
			Final[1] = y;
			TempStackable->HitSprites[1] = TempStackable->Collisions[1];
		}
	}
	TempStackable->XCollision = Final[0];
	TempStackable->YCollision = Final[1];

	//TempStackable
	//Up to 3 Sprite*'s for things we WOULD hit if moving to that position.
	//Up to 2 integers, for the 'safe' position to TP
	 

};

ReMapSprite(Sprite* ObjectSprite); //remap based on Lastviable position. NOT xPos, yPos.
CheckOverlap(Sprite* ObjectSprite);
RemoveSpriteFromMap(Sprite* ObjectSprite);
MoveAllSprites() {
	std::vector<XYArr*> SpriteStacks = {};


	//while Que is not empty, or while completed is not all complete or something
	for (int i = 0; i < AllSprites.size(); i++) {
		
		if (Completed[i] == 0) {   //check on init, then don't call again at the start of MoveAllSprites. SO GET IT OUTTA HERE when implementing, make speerate function call on initalization.
		 	//MoveV
			CheckOverlap(AllSprites[i]); //sets ExVec. If editted, we want to edit Travel accordingly... until you're free from influence. SO 
			//CheckOverlap 
			//1)Reads what tile on map your on.
			//2)Contorts ExVec based on those values, and your initial xVec, yVec values.
			//3)Edits ExpectedTravel Acccordingly (Depending on the overlap, you may say subtract the Controt from this immediately, and then pick up where you left off. Not sure what the default would be.
			//4)Edits TravelControt accordingly. 
			//flags TravelControt as being used or unsued. 



			//Move^
			//good hereV
			if (AllSprites[i]->ExVec[0] != 0 && AllSprites[i]->ExVec[1]!=0) { //no need to check th efuture if your still man! <-still check overlap however.
				RemoveSpriteFromMap(AllSprites[i]);
				XYArr* TempStackable = new XYArr;
				CheckFuture3(AllSprites[i], TempStackable);


				//determine direction, do what is necessary: can only hit 0, 1, or 2 sprites (for collision at least)
				//HandleCollision() -? not sure exactly what I want to do wit hthis below code, whether here or in new function
					if (TempStackable->HitSprites[0] != nullptr) {
						if (TempStackable->HitSprites[1] != nullptr) {
							//HEY is one or the other not completed? if so, your LAST viable position should not change 
							//if both completed, your last viable position should be updated.
							//edit your Travel or Travel Controt
							//if one is not completed, then DON'T change last viable poistion, add to stack. recheck <-this could be improved by asking about the ran into sprites direction of travel
							//In the event we ahve two victims, in each others collision... cancel out the shared collision axis, UNLESS it's diagonal straight on. then push to stack! (if not emptied because of this, because it will just move again until it's actually completed. idk if we can edit expected vec (likely not with overlap doing that), so just keep moving til complete, OR if 
							// you are colliding with sprites taht are trying to move into you. If your creationorder is higher than both or one, move appropriately).
							//IF you actually succeeded in moving someplace, check overlap. Mark collisions.
						}
						else if (TempStackable->HitSprites[2] != nullptr) {}
						else {}
					}
					else if (TempStackable->HitSprites[1] != nullptr) {
						if (TempStackable->HitSprites[0] != nullptr) {}
						else if (TempStackable->HitSprites[2] != nullptr) {}
						else {}
					}
					else if (TempStackable->HitSprites[2] != nullptr) {
						if (TempStackable->HitSprites[0] != nullptr) {}
						else if (TempStackable->HitSprites[1] != nullptr) {}
						else {}
					}
					else {
						//hit NOTHING
						//edit Travel or Travel contort,
						//update last viable position -maybe redudant
					}


					ReMapSprite(AllSprites[i]);

					//only mark as complete, if your actually done moving, still torn on how to handle Travel Controt, whether I should just end it's movement, or go back to the initial, or if I should edit the original based of the controt.
					if (AllSprites[i]->UseControt) {
						if (AllSprites[i]->TravelControt[0]=0 && AllSprites[i]->TravelControt[1] = 0) {
							Completed[i] = 1;
						}
					}
					else {
						if (AllSprites[i]->Travel[0] = 0 && AllSprites[i]->Travel[1] = 0) {
							Completed[i] = 1;
						}
					}

					//if not completed
					if (Completed[i] != 1) {
						SpriteStacks.push_back(TempStackable);
					}
					else {
						//FIND INVESTIGATION INDEXS
						for (int x = 0; x < SpriteStacks.size(); x++) {
							SpriteStacks[x];
							if (SpriteStacks[x]->HitSprites[0]==AllSprites[i]) {
								SpriteStacks[x]->HitSprites[0] = nullptr;
									//investigate index
							}
							if (SpriteStacks[x]->HitSprites[1] == AllSprites[i]) {}
							if (SpriteStacks[x]->HitSprites[2] == AllSprites[i]) {}
						}

						//psuedo
						//for all investigate index {
							//if HitSprites is completely empty ->add to Victim List 
						//}
						 



						//Handle Victim List until empty



					}
					

			}


		}





	}


}